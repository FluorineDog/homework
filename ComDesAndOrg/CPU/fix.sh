echo "v2.0 raw" > tester.hex && 
Mars dog-test.asm mc CompactDataAtZero dump .text HexText dog-test-tmp.hex > /dev/null && 
cat dog-test-tmp.hex >> tester.hex && 
rm dog-test-tmp.hex

