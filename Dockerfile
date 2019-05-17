FROM frolvlad/alpine-glibc
RUN mkdir /app

ADD ./generate_load /app
RUN chmod +x /app/generate_load

CMD ["/app/generate_load"]
