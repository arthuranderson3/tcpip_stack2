FROM alpine as tcpip_stack-build-env
RUN apk add --no-cache build-base cmake
WORKDIR /app
COPY . .
RUN cmake -S ./src/. -B build
RUN cmake --build build 
WORKDIR /app/build
RUN ctest .

#FROM alpine
#COPY --from=tcpip_stack-build-env /app/build/tcpip2 /app/tcpip2
#WORKDIR /app
#RUN ./tcpip2
