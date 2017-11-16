FROM resin/rpi-raspbian

MAINTAINER Alexander Bubeck <alexander.bubeck@zuehlke.com>

WORKDIR /root/
COPY build/blinktest blinktest

CMD ["./blinktest"]