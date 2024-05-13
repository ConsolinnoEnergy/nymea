ARG BASE
FROM ${BASE}
ARG TARGETARCH
COPY setup_build_env.sh .
RUN ./setup_build_env.sh $TARGETARCH
ENV DEB_BUILD_OPTIONS=nocheck
