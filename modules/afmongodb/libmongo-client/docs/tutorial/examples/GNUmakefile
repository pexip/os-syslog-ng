# NOTE: This Makefile assumes that a recent enough version of
# libmongo-client is installed!
#
# It will NOT work in the build directory, without an installed
# libmongo-client library.

TUTORIAL_PROGRAMS	= tut/bson_build \
			  tut/bson_traverse \
			  tut/mongo_sync \
			  tut/mongo_sync_cmd_create \
			  tut/hl_client \
			  tut/json2bson

LMC_CFLAGS		= $(shell pkg-config --cflags libmongo-client)
LMC_LIBS		= $(shell pkg-config --libs libmongo-client)

JSON_C_CFLAGS		= $(shell pkg-config --cflags json)
JSON_C_LIBS		= $(shell pkg-config --libs json)

TUT_CFLAGS		= ${LMC_CFLAGS}
TUT_LIBS		= ${LMC_LIBS}

all: ${TUTORIAL_PROGRAMS}
clean:
	rm -f ${TUTORIAL_PROGRAMS}
	-rmdir tut/

tut/json2bson: TUT_CFLAGS += ${JSON_C_CFLAGS}
tut/json2bson: TUT_LIBS += ${JSON_C_LIBS}
${TUTORIAL_PROGRAMS}: tut/%: tut_%.c
	@install -d tut
	${CC} ${TUT_CFLAGS} ${CFLAGS} ${TUT_LIBS} ${LDFLAGS} $< -o $@

.PHONY: all clean
