#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Hàm function operators ở đây được sử dụng để gọi các hàm min, max và gcd
using functionOperator = T(*)(T, T);

// folderName là folder lưu các bảng sparse table
const std::string folderName = "dataGenerator";
// count.txt được sử dụng để theo dõi có bao nhiêu bảng được tạo
const std::string countFile = "count.txt";
// Theo file homework, số bảng tối đa được tạo là 5
const int MAX_FILE = 5;

// Utility namespace containing mathematical utility functions and initializations
namespace Utility {
    // Maximum limit for precomputed logarithms
    // We assume that the input size is less than or equal 2 million elements
    constexpr int MAXN = 2E6;
    // Array to store logarithm values
    // we store the integer part of log(number)
    int lg2[MAXN + 1];

    // Function to initialize logarithm values using a precomputed approach
    // Static function to initialize logarithm values up to MAXN
    static void init() {
        // Base case: log2(1) = 0
        lg2[1] = 0;

        // Iteratively calculate logarithm values for integers from 2 to MAXN
        for (int i = 2; i <= MAXN; ++i) {
            // Logarithm value of i is calculated as log2(i) = log2(i / 2) + 1
            lg2[i] = lg2[i / 2] + 1;
        }
    }


    // Template function to find the maximum of two values
    template<typename T>
    T max(T lhs, T rhs) {
        return lhs > rhs ? lhs : rhs;
    }

    // Template function to find the minimum of two values
    template<typename T>
    T min(T lhs, T rhs) {
        return lhs < rhs ? lhs : rhs;
    }

    // Template function to calculate the greatest common divisor using Euclidean algorithm
    template<typename T>
    T gcd(T a, T b) {
        if (a == 0) return b;
        return gcd(std::abs(b) % std::abs(a), std::abs(a));
    }

    // Struct to initialize logarithm values when instantiated
    // An instance of this struct is initalized in order to invoke the 
    //  constructor which calls the init() function 
    //  to compute log[i] in range 1..MAXN
    struct InitUtility {
        // Constructor that automatically triggers initialization upon instantiation
        InitUtility() {
            init(); // Invokes the initialization function
        }
    };

    // Static instance of InitUtility to trigger initialization upon program startup
    // When the program starts, this static instance is created and
    //  the default constructor is called, therefore, init() is called.
    static InitUtility initializer;
}


// Function to prepare the environment for database operations
// This function create the database folder in order to
//  save the sparse table files
// It also create count.txt which keep track
//  the number of table files in the current database.
void prepare() {
    // Creating a command to make a directory for the database
    std::string command = "mkdir /p " + DATABASE_FOLDERNAME;
    // Running the command using system call
    system(command.c_str());

    // Generating the file path for the count file within the database folder
    std::string filePath = DATABASE_FOLDERNAME + "/" + COUNT_FILENAME;

    // Checking if the count file exists
    std::ifstream inputFile(filePath);
    if (inputFile.is_open()) {
        // File exists; close the input file stream
        inputFile.close();
    } else {
        // File does not exist or cannot be opened; create a new count file
        std::ofstream outputFile(filePath);
        // Initializing the count value to 0 in the new count file
        outputFile << 0;
        // Close the output file stream after writing
        outputFile.close();
    }
}

// Function to convert tableType into a corresponding binary operator function for int64_t
binaryOperator<int64_t> convertBinOp(char *tableType) {
    binaryOperator<int64_t> binOp; // Initialize the binary operator

    // Check the input string to determine the appropriate operation
    if (strcmp(tableType, "MIN") == 0) {
        binOp = Utility::min<int64_t>; // Assigns the minimum function for int64_t
    } else if (strcmp(tableType, "MAX") == 0) {
        binOp = Utility::max<int64_t>; // Assigns the maximum function for int64_t
    } else if (strcmp(tableType, "GCD") == 0) {
        binOp = Utility::gcd<int64_t>; // Assigns the GCD function for int64_t
    } else {
        binOp = nullptr; // Invalid table type, assign nullptr
    }

    return binOp; // Return the selected binary operator
}

// Here I use templated class 
//  so that I can create SparseTable
//  of various types: int, long long, float, double, etc
template<typename T>
class SparseTable {
private:
    std::size_t size; // Size of the table
    std::int32_t height; // Height of the table
    std::vector<std::vector<T>> table; // 2D vector representing the sparse table
    binaryOperator<T> op; // Binary operator used for computations

public:
    SparseTable() : 
        size(0), height(0), table() 
    {} // Default constructor initializing empty table

    // Constructor initializing the table with provided vector, size, and binary operator function
    SparseTable(const std::vector<T> &arr, std::size_t size, binaryOperator<T> binOp) {
        init(arr, size, binOp);
    }

    // Method to initialize the sparse table with the provided vector, size, and binary operator function
    void init(const std::vector<T>& arr, std::size_t size, binaryOperator<T> binOp) {
        op = binOp; // Assigns the provided binary operator to op
        this->size = size; // Assigns the given size to the table size
        height = Utility::lg2[size] + 1; // Calculates the table height based on the logarithm utility

        // Resizes the table to the calculated height and size, filled with zeroes
        table.resize(height, std::vector<T>(size, T(0)));
        
        // Fills the first row of the table with elements from the input vector (arr)
        for (std::size_t i = 0; i < size; ++i) {
            table[0][i] = arr[i];
        }

        // Populates the rest of the table using the binary operator function
        for (std::size_t  i = 1; i < height; ++i) {
            for (std::size_t  j = 0; j + (1ULL << i) - 1 < size; ++j) {
                table[i][j] = op(table[i - 1][j], table[i - 1][j + (1ULL << (i - 1))]);
            }
        }
    }

    // Method to query the table for a specific range and return the result
    T query(int lowerBound, int upperBound) {
        lowerBound = Utility::max<int>(lowerBound, 0); // Ensures lowerBound is within bounds
        upperBound = Utility::min<int>(upperBound, size - 1); // Ensures upperBound is within bounds

        if (lowerBound > upperBound) { // Checks for an invalid range
            std::cerr << "Invalid range";
            return -1;
        }

        int k = Utility::lg2[upperBound - lowerBound + 1]; // Calculates the logarithm value

        // Returns the result by applying the binary operator function over the specified range
        return op(table[k][lowerBound], table[k][upperBound - (1 << k) + 1]);
    }

    // Method to save the table contents to a file
    void save(char* tableName, char* tableType) {
        // Prepare for saving: create count file, handle existing file, and count
        prepare();

        // Open the count file to read and write counts of saved tables
        std::fstream countFile(DATABASE_FOLDERNAME + "/" + COUNT_FILENAME,
                        std::ios::in | std::ios::out);
        int count = 0;
        if (countFile.good()) {
            countFile >> count; // Read the current count of saved tables
            if (count == MAX_FILE) { // Check if the maximum file count is reached
                std::cerr << "Max file exceeded!\n"; // Display error message
                return; // Exit the function
            }
        }

        // Create or overwrite file to save table data
        std::string fileName = tableName;
        fileName += ".st";
        std::string filePath = DATABASE_FOLDERNAME + "/" + fileName;
        std::ifstream inputFile(filePath); // Check if the file already exists
        if (inputFile.is_open()) {
            // File exists, decrement the count as it will be overwritten
            inputFile.close();
            --count;
        }

        std::ofstream outputFile(filePath); // Open the file for writing

        // Write table metadata and data to the file
        std::cout << "\n"; // Print newline for formatting
        outputFile << tableType << "\n"; // Write the table type to the file
        outputFile << size << " " << height << "\n"; // Write size and height of the table
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << table[i][j] << " "; // Print table element to console
                outputFile << table[i][j] << " "; // Write table element to the file
            }
            std::cout << "\n"; // Move to the next line in the console
            outputFile << "\n"; // Move to the next line in the file
        }
        outputFile.close(); // Close the file

        count++; // Increment the count for saved files
        countFile.clear();
        countFile.seekg(std::ios_base::beg);
        countFile << count; // Update the count in the count file
        countFile.close(); // Close the count file
    }

    // Method to load a saved table from a file
    bool load(char *tableName) {
        std::string fileName = tableName;
        fileName += ".st";
        std::fstream ifs(DATABASE_FOLDERNAME + "/" + fileName, std::ios::in);
        if (!ifs.is_open()) {
            std::cerr << "Cannot read file!\n"; // Display error if file cannot be opened
            return false; // Return false to indicate failure in loading
        }
        char tableType[10] = {};
        ifs >> tableType; // Read the table type from the file
        op = convertBinOp(tableType); // Convert and assign the binary operator based on table type
        ifs >> size >> height; // Read the size and height of the table
        table.resize(height, std::vector<int64_t>(size)); // Resize the table
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < size; ++j) {
                ifs >> table[i][j]; // Read and assign table elements from the file
            }
        }
        ifs.close(); // Close the file
        return true; // Return true to indicate successful loading of the table
    }
};

// Create a sparse table with the specified table name, table type, and sequence data
void makeCommand(char *tableName, char *tableType, char **seq, size_t seqSize) {
    // Convert table type to a binary operator for table operations
    binaryOperator<int64_t> binOp = convertBinOp(tableType);

    // Convert sequence data from char* to int64_t and store it in a vector
    std::vector<int64_t> numSeq(seqSize);
    for (std::size_t i = 0; i < seqSize; ++i) {
        numSeq[i] = std::atoll(seq[i]);
    }

    // Initialize a SparseTable instance with the provided sequence and binary operator
    SparseTable<int64_t> st;
    st.init(numSeq, seqSize, binOp);

    // Save the initialized table to a file with the given table name and type
    st.save(tableName, tableType);
}

// Process query commands on a specified table within given bounds
void queryCommand(char *tableName, char *lowerBound, char *upperBound) {
    // Create an instance of SparseTable for executing queries
    SparseTable<int64_t> st;

    // Load the specified table, if successful, execute the query and print the result
    if (st.load(tableName)) {
        std::cout << st.query(std::atoi(lowerBound), std::atoi(upperBound)) << "\n";
    }
}

// Parse and interpret command line arguments for creating tables or executing queries
void parseArgument(int argc, char **argv) {
    using std::cerr;
    using std::cout;

    // Check the number of arguments and their validity
    if (argc < 5 || (strcmp(argv[1], "make") && strcmp(argv[1], "query"))) {
        cerr << "Invalid argument!\n"; // Display error message for invalid arguments
        cout << "Supported argument: \n";
        cout << "\t file make [Table_name] [Table_type] [Sequence]\n"; // Display usage for making a table
        cout << "\t file query [Table_name] [Lower_bound] [Upper_bound]\n"; // Display usage for querying a table
        exit(1); // Exit the program with an error code
    }

    if (!strcmp(argv[1], "make")) {
        // If the command is 'make', create a new table based on provided arguments
        makeCommand(argv[2], argv[3], argv + 4, argc - 4);    
    } else {
        // If the command is 'query', execute a query on the specified table within given bounds
        queryCommand(argv[2], argv[3], argv[4]);
    }
}

int main(int argc, char** argv) {
    parseArgument(argc, argv);
}