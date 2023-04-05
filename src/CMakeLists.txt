target_sources("${PROJECT_NAME}_lib" PRIVATE
    "utils/Complex.cpp"
    "utils/Vector2.cpp"
    "utils/Vector3.cpp"
    "utils/CommandLineOptions.cpp"
    "compute/FFT.cpp"
    "compute/Gaussian.cpp"
    "compute/PhillipsSpectrum.cpp"
    "rendering/Image.cpp"
    "rendering/Ray.cpp"
    "rendering/Camera.cpp"
    "rendering/Object.cpp"
    "rendering/Scene.cpp"
    "rendering/Texture.cpp")