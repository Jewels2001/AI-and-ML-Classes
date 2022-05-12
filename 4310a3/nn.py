
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.datasets import fetch_20newsgroups
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPClassifier
from sklearn.pipeline import Pipeline
from sklearn.pipeline import make_pipeline

from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.metrics import classification_report, accuracy_score

categories = ['comp.sys.ibm.pc.hardware', 'comp.os.ms-windows.misc',
              'misc.forsale', 'rec.sport.hockey', 'rec.sport.baseball','sci.space']
print("hi")
newsgroups_train = fetch_20newsgroups(subset='train', shuffle=True,
                                                 remove=('headers', 'footers',
                                                         'quotes'),
                                                 categories=categories)
newsgroups_test = fetch_20newsgroups(subset='test', shuffle=True,
                                                remove=('headers', 'footers',
                                                        'quotes'),
                                                categories=categories)


# targets, frequency = np.unique(mydata_train.target, return_counts=True)
# count_vect = CountVectorizer(stop_words='english')


model = make_pipeline(TfidfVectorizer(), MLPClassifier(hidden_layer_sizes=(100,)))
model.fit(newsgroups_train.data, newsgroups_train.target)
labels = model.predict(newsgroups_test.data)


def predict_category(s, train=newsgroups_train, model=model):
    pred = model.predict([s])
    return train.target_names[pred[0]]


print(predict_category('their team took to the ice'))

print(predict_category('contract worth millions of dollars'))


print(model.score(newsgroups_test.data, newsgroups_test.target))
print(classification_report(newsgroups_test.target, labels))
