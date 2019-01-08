FROM alpine:3.8 AS build

RUN apk update
RUN apk add make gcc musl-dev

RUN mkdir -pv /bloaty
COPY . /bloaty/
RUN chown -R root:root /bloaty
WORKDIR /bloaty
RUN make

FROM alpine:3.8

COPY --from=build /bloaty/bloaty /bin
RUN chmod +x /bin/bloaty
ENTRYPOINT ["/bin/bloaty"]
