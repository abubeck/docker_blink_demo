
# Introduction into source code
The source code uses the bcm2835 library to light up LEDs on the blinkt! extension of the raspberry pi. The main program implements the larson animation from the blinkt python examples.

# Crosscompiling with docker

Setup cross compiling toolchain. Instead of using dockcross directly we use an additional overlay to install possible dependencies or customize the setup.

    cd cross_setup
    docker build -t myrbcross .
    docker run --rm myrbcross > ./myrbcross
    chmod +x myrbcross

Use docker to build project with dockcross

    ./cross_setup/myrbcross cmake -Bbuild -H. -GNinja
    ./cross_setup/myrbcross ninja -Cbuild

Copy binary to raspy and show it is running (substitute YOUR_RP_IP)

    scp build/blinktest pirate@YOUR_RP_IP:/home/pirate/

On raspberry pi (LEDs should light up)

    sudo ./blinktest    

# Packaging applications with docker and transfer to raspberry
Package binary into Dockerfile and run docker build to build binary (siehe Dockerfile)

    docker build -t blinktest_cross cross_target

Check if you have locally the image in the image registry

    docker images    

To transfer the image to the raspberry pi you have to use the docker registry. Login into the registry (here our private azure registry) and push the image to the registry:

    docker login iotexperiments.azurecr.io
    docker tag blinktest_cross iotexperiments.azurecr.io/emx/blinktest_cross
    docker push iotexperiments.azurecr.io/emx/blinktest_cross

Get the docker image on raspy and see the LEDs blink again. (REGISTRY_IP is the IP address of your working machine)

    docker login iotexperiments.azurecr.io
    docker pull iotexperiments.azurecr.io/emx/blinktest_cross
    docker run -it --cap-add SYS_RAWIO --device /dev/gpiomem iotexperiments.azurecr.io/emx/blinktest_cross

# 2nd approach: Cross compilation with qemu
Alternative to the classical cross compilation approach is the compilation within a simulated target architecture using qemu. (see https://resin.io/blog/building-arm-containers-on-any-x86-machine-even-dockerhub/) This allows the packaging of the application into other distributions for which no cross toolchain exists. Here we show the compilation into alpine linux.

Compile within cross build container (multistage version)

    rm -rf build
    docker build . -f Dockerfile.multistage -t emx/blink_demo
    docker tag emx/blink_demo iotexperiments.azurecr.io/emx/blink_demo
    docker push iotexperiments.azurecr.io/emx/blink_demo

Now run the (much smaller) image on raspberry pi.

    docker pull iotexperiments.azurecr.io/emx/blink_demo
    docker run -it --cap-add SYS_RAWIO --device /dev/mem iotexperiments.azurecr.io/emx/blink_demo

# 3rd approach: Qemu based crosscompilation with multistage builds


Inspect the image sized on the raspberry pi:

    docker images   


# Open questions:
* Host2host transfer of images without registry
