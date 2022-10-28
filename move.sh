rm FILES
for x in $(find finaly -type f); do
	stripped_name=$(echo "$x" | sed 's/^.*\///')
	loc=$(find code -name "$stripped_name")
	if [ -z "$loc" ]; then 
		echo "$x not found"
	else
		echo $loc >> FILES
		cp $x $loc
	fi
done
