#############################################################################
# Copyright (c) 2019 Balabit
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 as published
# by the Free Software Foundation, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# As an additional exemption you are allowed to compile & link against the
# OpenSSL libraries as published by the OpenSSL project. See the file
# COPYING for details.
#
#############################################################################

from utils.Yacc2Graph import yacc2graph


class BisonGraph():
    def __init__(self, yaccfile):
        with open(yaccfile, 'r') as f:
            yacc = f.read()
            self.graph = yacc2graph(yacc)

    def get_nodes(self):
        return list(self.graph.nodes)

    def _children_of_rule_sorted(self, node):
        children = []
        for child, arcs in self.graph[node].items():
            for _, arc in arcs.items():
                children.append((arc['index'], child))
        return [x[1] for x in sorted(children)]

    def get_children(self, node):
        if self.is_rule(node):
            return self._children_of_rule_sorted(node)
        else:
            return sorted(self.graph.successors(node))

    def get_parents(self, node):
        return sorted(self.graph.predecessors(node))

    def is_terminal(self, node):
        return len(list(self.graph.successors(node))) == 0

    def is_rule(self, node):
        if node not in self.get_nodes():
            raise Exception('Node not in graph: ' + node)
        try:
            int(node)
        except ValueError:
            return False
        return True

    def add_arc(self, from_node, to_node):
        if self.is_rule(from_node) and not self.is_rule(to_node):
            index = len(self.get_children(from_node))
            self.graph.add_edge(from_node, to_node, index=index)
        elif not self.is_rule(from_node) and self.is_rule(to_node):
            self.graph.add_edge(from_node, to_node)
        else:
            raise Exception('Arc must be added from non-rule to rule or rule to non-rule: ' + from_node + '->' + to_node)

    def make_terminal(self, node):
        children = self.get_children(node)
        for child in children:
            self.graph.remove_edge(node, child)

    def remove(self, node):
        self.graph.remove_node(node)

    def _gather_tokens_from_rules(self, node, paths, stack):
        paths = paths.copy()
        for child in self.get_children(node):
            if self.is_terminal(child):
                if child == '$end':
                    break
                for i in range(len(paths)):
                    paths[i] += (child,)
            else:
                paths = self.get_paths(child, paths, stack)
        return paths

    def _gather_tokens_from_nonterminals(self, node, paths, stack):
        new_paths = []
        for child in self.get_children(node):
            new_path = self.get_paths(child, paths, stack)
            new_paths.extend(new_path)
        return new_paths

    def get_paths(self, node='$accept', paths=None, stack=None):
        if stack is None:
            stack = set()
        if paths is None:
            paths = [()]

        if node in stack:
            return paths
        stack.add(node)

        if self.is_rule(node):
            paths = self._gather_tokens_from_rules(node, paths, stack)
        else:
            paths = self._gather_tokens_from_nonterminals(node, paths, stack)

        stack.remove(node)
        return paths
