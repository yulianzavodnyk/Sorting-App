# Use an official Ubuntu as a parent image
FROM ubuntu:20.04
LABEL authors="Julian Zavodnyk"

# Set environment variables to avoid user prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    apt-transport-https \
    gnupg \
    software-properties-common \
    qt5-default \
    qttools5-dev-tools \
    g++ \
    libx11-dev \
    libxext-dev \
    libxrender-dev \
    libxrandr-dev \
    libxfixes-dev \
    libxcursor-dev \
    libxinerama-dev \
    libxi-dev \
    libgl1-mesa-glx \
    xauth \
    x11-apps \
    && apt-get clean

# Install a newer version of CMake from Kitware's official repository
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | apt-key add - && \
    apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main' && \
    apt-get update && \
    apt-get install -y cmake && \
    apt-get clean

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the current directory contents into working directory
COPY . .

# Build the project
RUN mkdir -p build && cd build && \
    cmake .. && \
    make

# Set the display environment variable for X11
ENV DISPLAY=host.docker.internal:0.0

# Run the executable
CMD ["./build/First_Year_CS_Coursework"]