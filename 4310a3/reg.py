
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

from sklearn.datasets import fetch_20newsgroups
from sklearn.linear_model import LogisticRegression

from sklearn.feature_extraction.text import TfidfVectorizer
# from sklearn.feature_extraction.text import CountVectorizer
# from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.pipeline import make_pipeline

from sklearn import metrics
from sklearn.pipeline import make_pipeline
from sklearn.pipeline import Pipeline
from sklearn.metrics import confusion_matrix
from sklearn.metrics import classification_report, accuracy_score

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

model = make_pipeline(TfidfVectorizer(), LogisticRegression())
model.fit(newsgroups_train.data, newsgroups_train.target)
labels = model.predict(newsgroups_test.data)


mat = confusion_matrix(newsgroups_test.target, labels)
sns.heatmap(mat.T, square=True, annot=True, fmt='d', cbar=False,
            xticklabels=newsgroups_train.target_names,
            yticklabels=newsgroups_train.target_names)
plt.xlabel('true label')
plt.ylabel('predicted label')

# classifier = Pipeline([
#     ('vec', CountVectorizer()),
#     ('tfidf', TfidfTransformer()),
#     ('classify', MultinomialNB()),
# ])


def predict_category(s, train=newsgroups_train, model=model):
    pred = model.predict([s])
    return train.target_names[pred[0]]


print(predict_category('their team took to the ice'))

print(predict_category('contract worth millions of dollars'))

# vectors_test = vectorizer.transform(newsgroups_test.data)

# # will train model with one command
# classifier.fit(newsgroups_train.data, newsgroups_train.target)

# plt.show()

# _test = newsgroups_test.data
# predicted=model.predict(_test)
# print(np.mean(predicted == newsgroups_test.target))

print(model.score(newsgroups_test.data, newsgroups_test.target))
print(classification_report(newsgroups_test.target, labels))
