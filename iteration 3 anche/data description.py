#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from datetime import datetime


# In[2]:


pd.set_option('display.max_columns', 20)
pd.set_option('display.max_rows', 20)
pd.set_option('display.width', 300)


# In[3]:


df = pd.read_csv('Y-2024.csv')


print(df.info(),'\n\n')

print(df.shape)


# In[4]:


df['sample.sampleDateTime'] = pd.to_datetime(df['sample.sampleDateTime'])

df['numeric_result'] = df['result'].apply(lambda x: 
    float(str(x).replace('<', '')) if pd.notnull(x) else np.nan)

df['below_detection'] = df['resultQualifier.notation'] == '<'
# number of miss data 
print(df.isnull().sum(),"\n")
# data type
print(df.dtypes,"\n")
# overview
print(df[['sample.sampleDateTime', 'determinand.label', 'result', 
          'numeric_result', 'below_detection', 'determinand.unit.label']].head(10),"\n")


# In[5]:


# data describtion
print(df.groupby('determinand.label')['numeric_result'].describe())

# unique value
print("\nnumber of samplingPoint:", df['sample.samplingPoint.label'].nunique())
print("number of determinand:", df['determinand.label'].nunique())
# list all determinand
#print(df['determinand.label'].unique())

# percent of below for all determinand
detection_summary = df.groupby('determinand.label')['below_detection'].agg(['count', 'sum'])
detection_summary['percentage_below'] = (detection_summary['sum'] / detection_summary['count'] * 100).round(2)

print(detection_summary)

# percent of below for all sampling point
detection_by_location = df.groupby(['sample.samplingPoint.label', 'determinand.label'])['below_detection'].agg(['count', 'sum'])
detection_by_location['percentage_below'] = (detection_by_location['sum'] / detection_by_location['count'] * 100).round(2)

detection_pivot = detection_by_location['percentage_below'].unstack()


print(detection_pivot)


# In[6]:


detection_summary_sorted = detection_summary.sort_values('percentage_below', ascending=False)
print(detection_summary_sorted)

detection_summary_count_sorted = detection_summary.sort_values('count', ascending=False)
print(detection_summary_count_sorted)


# In[ ]:




