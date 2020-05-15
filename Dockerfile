# get and configure an image
FROM debian:stretch-slim
RUN apt-get update
RUN apt-get install -y --no-install-recommends \
    ca-cacert \
    cmake \
    build-essential \
    libboost-all-dev \
    libssl-dev \
    wget \
    zlib1g-dev \
    clang


RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 40
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 60
RUN update-alternatives --config c++



# get and build wt4
WORKDIR /root/
RUN wget https://github.com/emweb/wt/archive/4.0.4.tar.gz
RUN tar zxf 4.0.4.tar.gz
WORKDIR /root/wt-4.0.4/build
RUN cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=OFF ..
RUN make -j2 install
RUN ldconfig

# build our app
WORKDIR /root/SIR_calculator
ADD . /root/SIR_calculator
RUN g++ -o sir_calculator ./src/main.cpp ./src/sir_interface.cpp -lwthttp -lwt
CMD /root/SIR_calculator/sir_calculator --docroot . --http-address 0.0.0.0 --http-port $PORT
