import numpy as np
import matplotlib.pyplot as plt

# Function to compute the given equation
def io_operations_equation(N, b, n):
    return (2 * N / (b * np.log2(n))) * np.log2(N / b)

# Input: array of N records and actual I/O operations
N_values = np.array([100, 1000, 10000, 100000, 1000000])  # Example N values (you can replace these)
io_operations_actual = np.array([500, 600, 700, 800, 900])  # Replace with your actual I/O operations
b = 1024  # Replace with your chosen value for b (block size)
n = 16    # Replace with your chosen value for n (number of tapes)

# Compute theoretical I/O operations
io_operations_theoretical = io_operations_equation(N_values, b, n)

# Plotting
plt.figure(figsize=(10, 6))
plt.loglog(N_values, io_operations_actual, 'o-', label='Actual I/O Operations')
plt.loglog(N_values, io_operations_theoretical, 's-', label='Theoretical I/O Operations')

# Adding labels, title, and legend
plt.xlabel('Number of Records (N)', fontsize=12)
plt.ylabel('I/O Operations', fontsize=12)
plt.title('I/O Operations: Actual vs Theoretical', fontsize=14)
plt.legend()
plt.grid(which='both', linestyle='--', linewidth=0.5)
plt.show()
