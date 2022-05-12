# By: Julie Wojtiw-Quo
# 4310 A3 - Q1

# 4310 - Q2
import matplotlib.pyplot as plt
# import numpy as np
import seaborn as sns

from sklearn.datasets import fetch_20newsgroups

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn import metrics
from sklearn.pipeline import make_pipeline
from sklearn.metrics import confusion_matrix

categories = ['comp.sys.ibm.pc.hardware', 'comp.os.ms-windows.misc',
              'misc.forsale', 'rec.sport.hockey', 'rec.sport.baseball','sci.space']
print("hi")
newsgroups_train = fetch_20newsgroups(subset='train',
                                                 remove=('headers', 'footers',
                                                         'quotes'),
                                                 categories=categories)
newsgroups_test = fetch_20newsgroups(subset='test',
                                                remove=('headers', 'footers',
                                                        'quotes'),
                                                categories=categories)

model = make_pipeline(TfidfVectorizer(), MultinomialNB())
model.fit(newsgroups_train.data, newsgroups_train.target)
labels = model.predict(newsgroups_test.data)


mat = confusion_matrix(newsgroups_test.target, labels)
sns.heatmap(mat.T, square=True, annot=True, fmt='d', cbar=False,
            xticklabels=newsgroups_train.target_names,
            yticklabels=newsgroups_train.target_names)
plt.xlabel('true label')
plt.ylabel('predicted label')




def predict_category(s, train=newsgroups_train, model=model):
    pred = model.predict([s])
    return train.target_names[pred[0]]


print(predict_category('their team took to the ice'))

print(predict_category('contract worth millions of dollars'))

# vectors_test = vectorizer.transform(newsgroups_test.data)

plt.show()
