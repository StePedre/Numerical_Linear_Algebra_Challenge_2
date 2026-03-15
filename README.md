# Singular Value Decomposition and Image Compression

**Team:** Ettore Cirillo, Angelo Notarnicola, Stefano Pedretti

## 📌 Overview
This challenge was developed for the Numerical Linear Algebra course (A.A. 2024/2025). The primary goal is to apply the singular value decomposition (SVD) to image compression and noise reduction.

## 🛠️ Technologies
* **Language:** C++.
* **Libraries:** Eigen library and LIS library.
* **Core Concepts:** Singular Value Decomposition, eigenvalue problems, and data compression.

## 🚀 Key Features
* **Image Compression:** Implemented truncated SVD to approximate image matrices, significantly reducing the amount of data needed for storage.
* **Noise Reduction:** Applied SVD techniques to filter noise from artificially corrupted images, such as a generated black and white checkerboard.
* **Numerical Solvers:** Computed the largest eigenvalues of matrices using both the Eigen library and iterative solvers from the LIS library, achieving a strict tolerance.
