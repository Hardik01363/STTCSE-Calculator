FROM ubuntu:latest

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install -y build-essential
WORKDIR /adder_app
ADD ./adder/ ./
RUN make clean; make
ENTRYPOINT ["./adder"]
