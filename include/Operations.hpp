#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace HTNODE
{

    template <typename K, typename V>
    struct HuffNode
    {
        HuffNode(K Key, V Value = 0, HuffNode *Left = nullptr, HuffNode *Right = nullptr)
        {
            key = Key;
            value = Value;
            left = Left;
            right = Right;
        }
        K key;
        V value;
        HuffNode *left;
        HuffNode *right;
        bool operator<(HuffNode<K, V> &n)
        {
            return value > n.value;
        }
    };
    template <typename K, typename V>
    void printAll(const HuffNode<K, V> *Root)
    {
        if (Root)
        {
            printAll(Root->left);
            printAll(Root->right);
            std::cout << Root->key << ":" << Root->value << endl;
        }
    }
    template <typename K, typename V>
    void binary(const HuffNode<K, V> *Root, string str1,map<char,string> &HuffCode)
    {
        if (Root)
        {
            if (Root->key != '@')
            {
                HuffCode.insert(pair<char, string>(Root->key, str1));
            }

            binary(Root->left, str1 + '0',HuffCode);
            binary(Root->right, str1 + '1',HuffCode);
        }
    }
    template <typename K, typename V>
    void Unbinary(const HuffNode<K, V> *Root, string str2,map <string , char> &Huffuncode)
    {
        if (Root)
        {
            if (Root->key != '@')
            {
                Huffuncode.insert(pair<string, char>(str2, Root->key));
            }

            Unbinary(Root->left, str2 + '0',Huffuncode);
            Unbinary(Root->right, str2 + '1',Huffuncode);
        }
    }

}
template <class K, class V>
class compare
{
public:
    bool operator()(HTNODE::HuffNode<K, V> *n1, HTNODE::HuffNode<K, V> *n2)
    {
        return n1->value > n2->value;
    }
};

priority_queue<HTNODE::HuffNode<char, int> *, vector<HTNODE::HuffNode<char, int> *>, compare<char, int>>  Maketree (string dna)
{
    priority_queue<HTNODE::HuffNode<char, int> *, vector<HTNODE::HuffNode<char, int> *>, compare<char, int>> pq1;
    map<char, int> dnaCounter;
    for (char &c : dna)
    {
        dnaCounter[c]++;
    }

    for (auto &node : dnaCounter)
    {
        HTNODE::HuffNode<char, int> *mariem = new HTNODE::HuffNode<char, int>(node.first, node.second);
        pq1.push(mariem);
    }
    while (pq1.size() != 1)
    {
        auto *node1 = pq1.top();
        pq1.pop();
        auto *node2 = pq1.top();
        pq1.pop();
        HTNODE::HuffNode<char, int> *parent = new HTNODE::HuffNode<char, int>('@', node1->value + node2->value, node1, node2);
        pq1.push(parent);
    }
    return pq1;
}

map<char, string> HuffCode;
vector<string> BiCompress( string dna)
{
    
    priority_queue<HTNODE::HuffNode<char, int> *, vector<HTNODE::HuffNode<char, int> *>, compare<char, int>>  pq11 = Maketree(dna);
    string freq;
    HTNODE::binary(pq11.top(), freq,HuffCode);
    vector<string> dnaencrypt;
    for (auto &char1 : dna)
    {
        auto maxs = HuffCode.at(char1);
        dnaencrypt.push_back(maxs);
    }
    return dnaencrypt;
}
void Compress (string dna)
{
    vector<string> compdna = BiCompress(dna);
    ofstream outFile;
    outFile.open("compress.txt",ios::binary);
    outFile.write( (char*) &compdna , sizeof(compdna));
    
    for (auto &val1:HuffCode)
    {
        outFile<<val1.first<<':'<<val1.second;
    }
    outFile.close();  
}
map<string, char> Huffuncode;
string BiDecompress(vector<string>dnaencrypt,string dna)
{
    priority_queue<HTNODE::HuffNode<char, int> *, vector<HTNODE::HuffNode<char, int> *>, compare<char, int>> pq12 = Maketree(dna);
    string freq2;
    HTNODE::Unbinary(pq12.top(), freq2,Huffuncode);
    string dnadecrypt;
    for (auto &string1 : dnaencrypt)
    {
        auto mins = Huffuncode.at(string1);
        dnadecrypt.push_back(mins);
    }
    return dnadecrypt;
}
void Decompress(vector<string>dnaencrypt,string dna)
{
    string decompdna = BiDecompress(dnaencrypt,dna);
    ofstream outFile2;   
    outFile2.open("decompress.txt");
    outFile2<<decompdna;
    outFile2.close();
}

