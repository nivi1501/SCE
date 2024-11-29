

## Implementation of the simantaneous compression and encryption scheme. 

### Pre-requisites:

Boost library version - 1.71<br />
GCC - 9.4<br />
zstd library version - 1.4.5<br />
Optimization level - 03

### System configuration:
The code is tested for the following system configuration<br />
Intel Core i5-8300H CPU<br />
#CPUs: 8 Cores<br />
Frequency 2.3 GHz <br />
DRAM: 8 GB <br />
L1:128 KB, L2:1 MB, L3:8 MB <br />
Linux kernel: 5.15 <br />
Operating System: Ubuntu 20.04

### Dataset preparation

The code is tested for images, pretrained and quantized neural network models and miscelleneous datasets from Kaggle. Users can download the dataset from the link given below:
1. Image dataset - https://sipi.usc.edu/database/database.php?volume=misc
2. Covid cases and deaths - https://www.kaggle.com/datasets/themrityunjaypathak/covid-cases-and-deaths-worldwide
3. IMDB movies dataset - https://www.kaggle.com/datasets/rajugc/imdb-top-250-movies-dataset
4. CO2-emissions-by-country - https://www.kaggle.com/datasets/ulrikthygepedersen/co2-emissions-by-country
5. Amazon product's ratings and reviews - https://www.kaggle.com/datasets/karkavelrajaj/amazon-sales-dataset
6. 3K conversations dataset for chatBot - https://www.kaggle.com/datasets/kreeshrajani/3k-conversations-dataset-for-chatbot
7. Medical cost personal datasets - https://www.kaggle.com/datasets/mirichoi0218/insurance 
8. Numerically generated ECG signal - https://www.kaggle.com/datasets/ahmadsaeed1007/ecg-signal

Dummy data generation using script - Run the command "gen_data.py". This script will generate the "data.csv" file which can be given as the input to the SCE code.

---

### Execution Instructions

#### Step 1: Update the Dataset Path
- Open the `main_time.cpp` file.
- Locate the `fileName` variable and update it with the absolute path of the dataset in your system.

#### Step 2: Compile the Code
Run the following command to compile the program:

```bash
make
```

#### Step 3: Run the Program
Execute the compiled file using:

```bash
./main_time
```

The script produces output similar to this -
![cryptoCompressed](https://github.com/user-attachments/assets/f6d148aa-6d16-4693-b8b9-092b40a0c38c)

The crypto-compressed datastream is saved in the file "crypto_compressed_data.dat"

---



### Decryption and Decompression Verification

#### Step 1: Update the Dataset Path
- Open the `main_time_verification.cpp` file.
- Locate the `fileName` variable and update it with the absolute path of the dataset in your system.

#### Step 2: Update the Makefile
- Open the `makefile` and update the `project` variable to `main_time_verification`.

#### Step 3: Compile the Code
Run the following command to compile:

```bash
make
```

#### Step 4: Run the Verification Program
Execute the verification program:

```bash
./main_time_verification
```

The program confirms that the decompression and decryption logic work correctly.

---

### NIST Verification for Randomness

#### Step 1: Download the NIST Suite
- Visit the [NIST Random Bit Generation Documentation](https://csrc.nist.gov/projects/random-bit-generation/documentation-and-software) and download the suite.

#### Step 2: Enable NIST Data Generation
- Open the `main_time.cpp` file.
- Uncomment the lines indicated for NIST test data generation.

#### Step 3: Compile the Program
Run the following command:

```bash
make
```

#### Step 4: Run the Program
Execute the program:

```bash
./main_time
```

#### Step 5: Run the NIST Tests
- Use the output data with the NIST suite to verify randomness.
- The code passes all NIST tests when a sufficient number of samples are provided.

---

### Comparison with AES

#### Run the command "./run.sh"

#### Details of the Bash Script `run.sh` 
1. **Compilation:**
   - The script compiles both `aes.cpp` and `main_time.cpp` (SCE algorithm) files using their respective `Makefile`s.
   - Ensures both executables (`aes` and `main_time`) are properly built.

2. **Execution:**
   - Executes both `aes` and `main_time` binaries.
   - Captures the time taken for each execution as printed in the command line output.

3. **Performance Analysis:**
   - Calculates the percentage improvement of the `main_time` algorithm over AES.
   - Outputs the improvement percentage

The script produces output similar to this -
![aes](https://github.com/user-attachments/assets/831f1911-2d12-4362-b4cf-9335345f08d6)

   
---

















