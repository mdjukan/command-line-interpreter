cd build

touch batch.in
echo "echo \"Hello from batch!\"" > batch.in
echo "time | tr \":\" \"-\"" >> batch.in
echo "date > file.out" >> batch.in
