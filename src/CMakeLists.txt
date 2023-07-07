target_sources("${PROJECT_NAME}_lib" PRIVATE
    "utils/Complex.cpp"
    "utils/Vector2.cpp"
    "utils/Vector3.cpp"
    "compute/FFT.cpp"
    "compute/Gaussian.cpp"
    "compute/Ocean.cpp"
    "rendering/Image.cpp"
    "rendering/Ray.cpp"
    "rendering/Camera.cpp"
    "rendering/Object.cpp"
    "rendering/Scene.cpp"
    "rendering/Hit.cpp")