# BlindWatch – Data Preparation, Conv1D Training, and Model Export

## 1. Collecting Gesture Data

Data is collected in **DeepCraft** with a connected IMU.

Required gestures:
- **circle**
- **shake**

Each gesture is performed in **two directions** (`left` and `right`).  
For each gesture/direction, record **2 samples with ~20 repetitions**:

- circle-left × 2  
- circle-right × 2  
- shake-left × 2  
- shake-right × 2  

## 1.1. How to Record a Single Sample

1. DeepCraft Studio → **Data** → **Record new signal**
2. Set the gesture label (e.g., `circle`)
3. Perform about **20 repetitions**:
   - gesture → 2s pause → gesture → 2s pause → …
4. Save the recording

## 1.2. Adding “Unlabeled” Data

For each gesture type, add **1 sample** of movements that are similar but **not** actual circle/shake gestures.  
Name these samples: **Unlabeled**.

## 2. Creating the Project

1. DeepCraft Studio → **File** → **New** → **Empty Classification Project**
2. Go to **Data** → **Add Data** and import all recordings
3. In **Labels/Classes**, keep only 3 classes:
   - `circle`
   - `shake`
   - `Unlabeled`

Assign all samples accordingly (left/right combined into the same class).

## 3. Data Split

In the **Data** tab, click **Redistribute Data** and set:

- **60%** – Training  
- **20%** – Validation  
- **20%** – Test  

## 4. Model Generation

1. Go to **Training** → **Generate Model List**
2. Select board: **Infineon**
3. Model Family: **Conv1D**
4. Leave all parameters at default and click **OK**
5. Delete all generated models **except the last one ending with `3`**  
   (`conv1d-medium-balanced-3`)

## 5. Preprocessor Configuration

Go to **Preprocessor** and set:

- **Input Shape:** 2.3  
- **Input Frequency:** 50 Hz  
- **Contextual Window (Sliding Window):**
  - Shape: `[100, 6]`
  - Frequency: **5 Hz**
  - Rate: **12 KB/s**

## 6. Training

1. Click **Start New Training Job...**
2. Configure:
   - **Batch Size:** 16  
   - **Split Count:** 16  
3. Selected model:
   - **conv1d-medium-balanced-3**
   - Input Shape: `[100, 6]`
   - Output Shape: `[3]`

Start training and review the Training/Validation/Test metrics.

## 7. Model Export

After training:

1. Open the **conv1d-medium-balanced-3** model
2. Go to the **Code Gen** tab and set:
   - Architecture: **Infineon PSoC**
   - Target Device: **PSoC 6**
   - Output File Prefix: **GestureDetectionModel**
   - C Prefix: **GESTURE_DETECTION_**
   - Preprocessor Acceleration: **CMSIS Floating Point (Float32)**
3. Click **Generate Code**

The generated file can be uploaded to BlindWatch.

