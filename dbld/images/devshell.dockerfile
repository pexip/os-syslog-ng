FROM balabit/syslog-ng-ubuntu-bionic:latest
LABEL maintainer="Andras Mitzki <andras.mitzki@balabit.com>, Laszlo Szemere <laszlo.szemere@balabit.com>, Balazs Scheidler <balazs.scheidler@oneidentity.com>"

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN=true
ENV LANG C.UTF-8
ENV OS_PLATFORM devshell

RUN /helpers/dependencies.sh enable_dbgsyms
RUN /helpers/dependencies.sh install_perf

RUN /helpers/dependencies.sh install_apt_packages
