#! /bin/sh

install -d coverage
rm -f coverage/report.txt

for src in ${SOURCES}; do
	case "$src" in
		*.c)
			obj=`echo $src | sed 's|\.c|.o|'`
			gc=`echo $src | sed 's|\.c|.gcno|'`
			if test -f "${builddir}/.libs/libmongo_client_la-$obj"; then
				objdir=${builddir}/.libs
			else
				objdir=${builddir}
			fi
			if ! test -f "${objdir}/libmongo_client_la-${gc}"; then
				continue
			fi
			gcov -b -f ${srcdir}/$src -o $objdir/libmongo_client_la-$obj >coverage/$src.cov
			;;
	esac
done

perl ${top_srcdir}/tests/tools/coverage-report.pl coverage/*.cov >coverage/index.xml
xsltproc ${top_srcdir}/tests/tools/coverage-report.xsl coverage/index.xml >coverage/index.html

for src in ${SOURCES}; do
	case "$src" in
		*.c)
			if ! test -f "${src}.gcov"; then
				continue
			fi

			perl ${top_srcdir}/tests/tools/coverage-report-entry.pl ${src}.gcov > coverage/${src}.gcov.html
			grep -A4 -m 1 "File '${srcdir}/$src'" coverage/$src.cov | grep -v "^--" >>coverage/report.txt
			echo >>coverage/report.txt
			;;
	esac
done

coverage=`(echo "scale=2"; echo -n "("; echo -n $(grep "Lines executed" coverage/report.txt | cut -d: -f2 | cut -d "%" -f 1) | sed -e "s, , + ,g"; echo ") / " $(grep -c "Lines executed" coverage/report.txt)) | bc -q`
lines=`(echo -n "("; echo -n $(grep "Lines executed" coverage/report.txt | cut -d% -f2- | cut -d " " -f3-) | sed -e "s, , + ,g"; echo ")") | bc -q`
echo "Overall coverage: $coverage% of $lines source lines" >>coverage/report.txt
