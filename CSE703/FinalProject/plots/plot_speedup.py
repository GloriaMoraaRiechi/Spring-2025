import matplotlib.pyplot as plt

# Real benchmark data
threads = [1, 2, 4, 8]
times = [9.35576, 9.09856, 8.67073, 9.02077]
speedup = [times[0] / t for t in times]

# Create plot
plt.figure(figsize=(8,6))
plt.plot(threads, speedup, marker='o', linestyle='-', linewidth=2)
plt.xlabel('Number of Threads', fontsize=14)
plt.ylabel('Speedup', fontsize=14)
plt.title('Speedup of k-mer Counting using OpenMP Tasks', fontsize=16)
plt.grid(True)
plt.xticks(threads)
plt.tight_layout()

# Save the plot as a file
plt.savefig('plots/speedup_plot.png')

print("✅ Speedup plot saved at 'plots/speedup_plot.png'!")

