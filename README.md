# **Route Manager**

## **Overview**
The **Route Manager** is a C program designed to analyze airline route data. It processes route information from a provided YAML file and outputs specific insights based on user-selected questions. The program handles data on airlines, countries, and airports, providing detailed analysis and generating a CSV file with the results.

---

## **Features**
1. **Question 1**: Finds the top **N airlines** offering the greatest number of routes with the destination country as **Canada**.
2. **Question 2**: Identifies the top **N countries** with the least appearances as a destination country in the route data.
3. **Question 3**: Lists the top **N destination airports** based on their frequency in the route data.

---

## **Input and Output**
### **Input**
- A YAML file containing airline route information.
- Command-line arguments specifying the type of question and other parameters.

### **Output**
- A CSV file named `output.csv` containing the analysis results.
- Console output summarizing the processed list and connection statistics.

---

## **How to Compile**
1. Ensure you have a C compiler installed (e.g., `gcc`).
2. Compile the program using:
   ```bash
   gcc -o route_manager route_manager.c list.c
   ```

---

## **How to Run**
1. Run the program with the following syntax:
   ```bash
   ./route_manager data=<path_to_file> question=<question_number> n=<number_of_results>
   ```
   - Replace `<path_to_file>` with the path to the YAML file.
   - Replace `<question_number>` with `1`, `2`, or `3`, depending on the analysis type.
   - Replace `<number_of_results>` with the number of results you want in the CSV output.

---

## **Examples**
### **Example 1**: Top airlines with the most routes to Canada
```bash
./route_manager data=routes.yaml question=1 n=10
```
**Output**: A CSV file `output.csv` containing the top 10 airlines.

---

### **Example 2**: Top countries with the least appearances
```bash
./route_manager data=routes.yaml question=2 n=5
```
**Output**: A CSV file `output.csv` listing the 5 countries with the least appearances.

---

### **Example 3**: Top destination airports
```bash
./route_manager data=routes.yaml question=3 n=15
```
**Output**: A CSV file `output.csv` containing the top 15 destination airports.

---

## **CSV Output Format**
The CSV file has two columns:
1. **subject**: The airline, country, or airport name (formatted according to the question).
2. **statistic**: The frequency or count related to the subject.

---
