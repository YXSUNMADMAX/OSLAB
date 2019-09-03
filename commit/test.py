import os, sys

filename = '10175110001_李明_Lab0'

def main():
    filename = sys.argv[1]
    name_list = filename.split('_')
    assert len(name_list) == 3
    assert len(name_list[0]) == 11
    assert name_list[2] == 'Lab0'

    files = os.listdir(filename)
    if len(files) != 3:
        print("error: the num of files is not right!")
        exit(1)
    assert '0a' in files
    assert '0b' in files
    assert (filename+'.pdf') in files

    sub_file = os.listdir(filename+'/0a')
    assert 's1.sh' in sub_file
    assert 's2.sh' in sub_file
    assert 's3.sh' in sub_file
    assert 's4.sh' in sub_file
    assert 'set_operation.c' in sub_file

    sub_fileb = os.listdir(filename+'/0b')
    assert 'fastsort.c' in sub_fileb
    print("ok!Congratulations!")

if __name__ == '__main__':
    main()
