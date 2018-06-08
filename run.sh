echo -e "Start building..."
mpicc *.c *.h -std=c99 -o build/mpihm
echo -e "Finished building."
echo -e "Start running:"
mpirun --allow-run-as-root -np 8 build/mpihm build/in.txt build/out.txt 2> build/error.txt
echo -e "Program exits"
echo -e "Please see error info at \`build/error.txt\`";