{
  "targets": [
    {
      "target_name": "ServosModule",
      "sources": [ "src/Wrapper/ServosModule.cpp","src/Wrapper/ServosWrapper.cpp",
      "src/Modules/Servos/Servos.cpp",
      "src/Libraries/PCA9685/PCA9685.cpp",
      ],
      "libraries": ["-l bcm2835","-l rt"]
    }
  ]
}
