import numpy as np
import matplotlib.pyplot as plt


def io_operations_equation(N, b, n):
    return (2 * N / (b * np.log2(n))) * np.log2(N / b)


N_values = np.array([100, 1000, 10000, 100000, 1000000, 10000000])  
io_operations_actual = np.array([10, 200, 2000, 40000, 400000, 4000000])  #  For constant size record
#io_operations_actual = np.array([2, 18, 180, 1800, 36172, 362520, 3625918])  # For random size record
b = 10 
n = 1001   


io_operations_theoretical = io_operations_equation(N_values, b, n)

plt.clf()
plt.figure(figsize=(10, 6))
plt.loglog(N_values, io_operations_actual, 'o-', label='Actual I/O Operations')
plt.loglog(N_values, io_operations_theoretical, 's-', label='Theoretical I/O Operations')

plt.xlabel('Number of Records (N)', fontsize=12)
plt.ylabel('I/O Operations', fontsize=12)
plt.title('I/O Operations: Actual vs Theoretical', fontsize=14)
plt.legend()
plt.grid(which='both', linestyle='--', linewidth=0.5)
plt.savefig('Plot_for_constant_size_record.png', dpi=300) 


