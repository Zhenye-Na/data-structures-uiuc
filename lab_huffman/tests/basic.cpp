#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fstream>
#include <unordered_map>

#include "../binary_file_reader.h"
#include "../decoder.h"
#include "../encoder.h"
#include "../huffman_tree.h"

using namespace std;

#define ADD_CHAR(c, freq) \
	do { \
		for( int i = 0; i < freq; ++i ) \
			text << c; \
	} while( 0 )

void buildText() {
	ofstream text( "tests/text.txt" );
	ADD_CHAR( 'a', 20 );
	ADD_CHAR( 'b', 30 );
	ADD_CHAR( 'c', 60 );
	ADD_CHAR( 'd', 40 );
	text.close();
}

void buildText2() {
	ofstream text( "tests/text.txt" );
    ADD_CHAR( 'a', 5 );
    ADD_CHAR( 'b', 6 );
    ADD_CHAR( 'c', 12 );
    ADD_CHAR( 'd', 13 );
    ADD_CHAR( 'e', 7 );
    ADD_CHAR( 'f', 8 );
	text.close();
}

void buildText( int start ) {
    ofstream text( "tests/text.txt" );
    for( char c = 'a'; c < 'f'; ++c ) {
        ADD_CHAR( c, start );
        start *= 2;
    }
    text << endl;
    text.close();
}

void compareBinaryFiles( string yourFile, string ourFile ) {
	ifstream yourBinary( yourFile, ios::binary );
	stringstream yours;
	yours << yourBinary.rdbuf();
	ifstream ourBinary( ourFile, ios::binary );
	stringstream ours;
	ours << ourBinary.rdbuf();
	if( yours.str() != ours.str() )
		FAIL( "Your binary file \"" + yourFile + "\" does not match our binary file \"" + ourFile + "\"");
}

HuffmanTree constructTree( string inputFile ) {
	ifstream toEncode( inputFile );
	stringstream data;
	data << toEncode.rdbuf();
	string str(data.str());
	unordered_map<char, int> freqs;
	for( size_t i = 0; i < str.length(); ++i )
		freqs[str[i]]++;
	vector<Frequency> buildWith;
	for( auto it = freqs.begin(); it != freqs.end(); ++it )
		buildWith.push_back( Frequency( it->first, it->second ) );
	return HuffmanTree( buildWith );
}

TEST_CASE("test_encoder_binary", "[weight=1]") {
	buildText();
	encoder::encodeFile( "tests/text.txt", "tests/test.bin", "tests/tree.huff" );
	compareBinaryFiles( "tests/test.bin", "tests/soln_test.bin" );
}

TEST_CASE("test_encoder_binary2", "[weight=1]") {
	buildText2();
	encoder::encodeFile( "tests/text.txt", "tests/test.bin", "tests/tree.huff" );
	compareBinaryFiles( "tests/test.bin", "tests/soln_test2.bin" );
}

TEST_CASE("test_encoder_writetree", "[weight=1]") {
	buildText();
	encoder::encodeFile( "tests/text.txt", "tests/test.bin", "tests/tree.huff" );
	compareBinaryFiles( "tests/tree.huff", "tests/soln_tree.huff" );
}

TEST_CASE("test_encoder_writetree2", "[weight=1]") {
	buildText2();
	encoder::encodeFile( "tests/text.txt", "tests/test.bin", "tests/tree.huff" );
	compareBinaryFiles( "tests/tree.huff", "tests/soln_tree2.huff" );
}

TEST_CASE("test_decode", "[weight=1]") {
	buildText();
	HuffmanTree htree = constructTree( "tests/text.txt" );
	BinaryFileReader bfile( "tests/soln_test.bin" );
	string decoded = htree.decodeFile( bfile );
	ifstream in( "tests/text.txt" );
	stringstream expected;
	expected << in.rdbuf();
	REQUIRE( expected.str() == decoded );
}

TEST_CASE("test_decode2", "[weight=1]") {
	buildText2();
	HuffmanTree htree = constructTree( "tests/text.txt" );
	BinaryFileReader bfile( "tests/soln_test2.bin" );
	string decoded = htree.decodeFile( bfile );
	ifstream in( "tests/text.txt" );
	stringstream expected;
	expected << in.rdbuf();
	REQUIRE( expected.str() == decoded );
}

TEST_CASE("test_decode_readtree", "[weight=1]") {
	buildText();
	decoder::decodeFile( "tests/soln_test.bin", "tests/soln_tree.huff", "tests/out.txt" );
	stringstream expected;
	stringstream decoded;
	ifstream expect( "tests/text.txt" );
	expected << expect.rdbuf();
	ifstream out( "tests/out.txt" );
	decoded << out.rdbuf();
	REQUIRE( expected.str() == decoded.str() );
}

TEST_CASE("test_decode_readtree2", "[weight=1]") {
	buildText2();
	decoder::decodeFile( "tests/soln_test2.bin", "tests/soln_tree2.huff", "tests/out.txt" );
	stringstream expected;
	stringstream decoded;
	ifstream expect( "tests/text.txt" );
	expected << expect.rdbuf();
	ifstream out( "tests/out.txt" );
	decoded << out.rdbuf();
	REQUIRE( expected.str() == decoded.str() );
}

TEST_CASE("test_the_works", "[weight=1]") {
    buildText( 2 );
    encoder::encodeFile( "tests/text.txt", "tests/test.bin", "tests/tree.huff" );
    decoder::decodeFile( "tests/test.bin", "tests/tree.huff", "tests/out.txt" );
    stringstream expected;
    stringstream decoded;
    ifstream expect( "tests/test.txt" );
    expected << expect.rdbuf();
    ofstream out( "tests/out.txt" );
    decoded << out.rdbuf();
    REQUIRE( expected.str() == decoded.str() );
    compareBinaryFiles( "tests/tree.huff", "tests/soln_tree_2.huff" );
    compareBinaryFiles( "tests/test.bin", "tests/soln_test_2.bin" );
}
