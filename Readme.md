# Introduction slides
# Introduction into source code
The source code uses the bcm2835 library to light up LEDs on the blinkt! extension of the raspberry pi.

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

    docker build -t blinktest .

Check if you have locally the image in the image registry

    docker images    

To transfer the image to the raspberry pi you have to use the docker registry. For testing purposes we are using a local docker registy. Spawn the registry and push the image to the registry:

    docker run -d -p 5000:5000 --restart=always --name registry registry:2
    docker tag blinktest localhost:5000/blinktest
    docker push localhost:5000/blinktest

Setup the registry on the raspberry pi. We have to add the registry to the trusted ones because we have no certificates setup. (REGISTRY_IP is the IP address of your working machine)

   * Create or modify /etc/docker/daemon.json and add
   { "insecure-registries":["REGISTRY_IP:5000"] }
   * sudo service docker restart

Get the docker image on raspy and see the LEDs blink again. (REGISTRY_IP is the IP address of your working machine)

    docker pull REGISTRY_IP:5000/blinktest
    docker run -it --cap-add SYS_RAWIO --device /dev/gpiomem blinktest

# Extend application
* Update program to a more complex animation
* Run the delivery pipeline: compile, build, push, pull, run




# Open questions:

* Automate pull/sync?
* Host2host transfer of images without registry
* Move to alpine