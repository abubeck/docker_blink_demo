FROM resin/rpi-raspbian
#FROM hypriot/rpi-alpine-scratch

MAINTAINER Alexander Bubeck <alexander.bubeck@zuehlke.com>

WORKDIR /root/
COPY build/blinktest blinktest

CMD ["./blinktest"]