{
  "targets": [
    {
      "target_name": "ServosModule",
      "sources": [
        "src/wrapper/ServosModule.cpp",
        "src/wrapper/ServosWrapper.cpp",
        "src/Servos.cpp",
        "src/libraries/robotois-PCA9685/PCA9685.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
