FILES=./Reste_Image/*
for f in $FILES
do 
    echo "Processing $f"
    python3 scriptClassification.py $f
done
