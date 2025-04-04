def split_csv_file(input_file, output_prefix, chunk_size=1000):
    """
    Splits a large CSV file into smaller chunks without loading everything into memory.
    
    :param input_file: Path to the input CSV file.
    :param output_prefix: Prefix for output chunk files.
    :param chunk_size: Number of lines per chunk.
    """
    with open(input_file, 'r', encoding='utf-8') as infile:
        header = infile.readline()  # Read the header
        lines = []
        part_number = 1

        for line_number, line in enumerate(infile, start=1):
            lines.append(line)

            if line_number % chunk_size == 0:
                output_file = f"{output_prefix}_part_{part_number}.csv"
                with open(output_file, 'w', encoding='utf-8') as outfile:
                    outfile.write(header)  # Write header in each chunk
                    outfile.writelines(lines)  # Write chunk lines

                print(f"Written: {output_file}")
                lines = []  # Clear for next chunk
                part_number += 1

        # Write any remaining lines in the last chunk
        if lines:
            output_file = f"{output_prefix}_partt_{part_number}.csv"
            with open(output_file, 'w', encoding='utf-8') as outfile:
                outfile.write(header)
                outfile.writelines(lines)
            print(f"Written: {output_file}")

    print(f"Splitting complete! {part_number} files created.")

# Example usage
input_file = "GSE282059_2B_FFPE_exprMat_file.csv"
output_prefix = "split_data"
split_csv_file(input_file, output_prefix)

