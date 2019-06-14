from math import log10
import getopt
import sys
import os
import string
import ast

vocab = {}
vocab_list = []
test_list = []
train_list = []
te = []
tr = []
num_positive = 0

def preprocess(test_file, train_file):
    global test_list
    global train_list
    global bag
    global vocab
    global vocab_list

    with open(test_file) as f:
        for line in f:
            temp = line.split(',')
            if len(temp) == 2:
                test_list.append(((temp[0].translate(None, string.punctuation)).lower(),temp[1].strip(temp[1].translate(None, string.digits))))

    with open(train_file) as f:
        for line in f:
            temp = line.split(',')
            if len(temp) == 2:
                train_list.append(((temp[0].translate(None, string.punctuation)).lower(),temp[1].strip(temp[1].translate(None, string.digits))))

    for index in train_list:
        for word in index[0].split(' '):
            if word and not word in vocab.keys():
                if index[1]:
                    vocab[word.lower()] = [1, 1, 0]
                else:
                    vocab[word.lower()] = [1, 0, 1]
            elif word in vocab.keys():
                if index[1]:
                    #increment word counter
                    vocab[word][0] += 1
                    #increment positive counter
                    vocab[word][1] += 1
                else:
                    #increment word counter
                    vocab[word][0] += 1
                    #increment negative counter
                    vocab[word][2] += 1

    write_to_files()

def classify():
    prob = {}
    prob_t = float(num_positive) / float(len(tr))
    prob_f = float(len(tr) - num_positive) / float(len(tr))
    result = open('results.txt', 'wb')

    for key, value in vocab.iteritems():
        prob[key] = [float(value[1]) / float(value[0]), float(value[1]) / float(value[0]), float(value[2]) / float(value[0]), float(value[2]) / float(value[0])]

    train = 1	
    for set in [tr, te]:
        count = 0
        for f in set:
            truep = 1.0
            falsep = 1.0
            for w in xrange(len(f)-1):
                if f[w]:
                    if vocab_list[w] in prob.keys():
                        truep += prob[vocab_list[w]][0]
                        falsep += prob[vocab_list[w]][3]

            if truep > falsep:
                if f[-1]: count += 1
            else:
                if not f[-1]: count += 1

	if train:
            print '\nTraining File: trainingSet.txt'
            print 'Testing File: trainingSet.txt\n'
 	    result.write('Training File: trainingSet.txt\n')
            result.write('Testing File: trainingSet.txt\n')
            print 'Accuracy on Training Set: ', (float(count)/float(len(set)))
            result.write('Accuracy on Training Set: ' + str(float(count)/float(len(set))) + '\n')
            print 'Number Correct: ', count
            result.write('Number Correct: ' + str(count) + '\n')
            print 'Training Set Size: ', len(set)
            result.write('Training Set Size: ' + str(len(set)) + '\n')
            result.write('\n\n')
            print '\n'
	    train = 0
	else:            
	    print '\nTraining File: trainingSet.txt'
            print 'Testing File: testSet.txt\n'
 	    result.write('Training File: trainingSet.txt\n')
            result.write('Testing File: testSet.txt\n')
            print 'Accuracy on Test Set: ', (float(count)/float(len(set)))
            result.write('Accuracy on Test Set: ' + str(float(count)/float(len(set))) + '\n')
            print 'Number Correct: ', count
            result.write('Number Correct: ' + str(count) + '\n')
            print 'Test Set Size: ', len(set)
            result.write('Test Set Size: ' + str(len(set)) + '\n')

def write_to_files():
    global vocab
    global test_list
    global train_list
    global te
    global tr
    global num_positive

    preprocessed_train = open('preprocessed_train.txt', 'wb')
    preprocessed_test  = open('preprocessed_test.txt', 'wb')

    preprocessed_train.write(', '.join(sorted(vocab.keys())) + ', classlabel\n')
    for index in train_list:
        tlist = sorted(index[0].split(' '))
        if '' in tlist: tlist.remove('')
        temp = []
        for word in sorted(vocab.keys()):
            if word in tlist:
                preprocessed_train.write('1,')
                temp.append(1)
            else:
                preprocessed_train.write('0,')
                temp.append(0)
            vocab_list.append(word)

        if index[1]: num_positive += 1
        preprocessed_train.write(str(index[1]) + '\n')
        temp.append(index[1])
        tr.append(temp)

    preprocessed_test.write(', '.join(sorted(vocab.keys())) + ', classlabel\n')
    for index in test_list:
        tlist = sorted(index[0].split(' '))
        if '' in tlist: tlist.remove('')
        temp = []
        for word in sorted(vocab.keys()):
            if word in tlist:
                preprocessed_test.write('1,')
                temp.append(1)
            else:
                preprocessed_test.write('0,')
                temp.append(0)
        preprocessed_test.write(str(index[1]) + '\n')
        temp.append(index[1])
        te.append(temp)

    preprocessed_train.close()
    preprocessed_test.close()

def main():
    test_file = 'testSet.txt'
    train_file = 'trainingSet.txt'

    #Check for files
    if os.path.isfile(test_file) and os.path.isfile(train_file):
        #pre-process
        preprocess(test_file, train_file)
        #classify
        classify()
    else:
        print "Not all required files are in the working directory."
        sys.exit(4)


if __name__ == "__main__":
        main()
