echo "v2.0 raw" > tester.hex && 
Mars a $1 mc CompactTextAtZero dump .text HexText dog-test-tmp.hex && 
cat dog-test-tmp.hex >> tester.hex && 
rm dog-test-tmp.hex

