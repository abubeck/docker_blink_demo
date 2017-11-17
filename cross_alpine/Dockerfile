FROM resin/armhf-alpine:3.6

RUN ["cross-build-start"]

MAINTAINER Alexander Bubeck <alexander.bubeck@zuehlke.com>

RUN apk add --update alpine-sdk coreutils cmake linux-headers ninja

RUN ["cross-build-end"]