from django.db import models
from django.utils import timezone
import datetime

# Create your models here.

class Blog(models.Model):

	author_choices = (
		('Reid', 'Reid'),
	)
	
	category_choices = (
		('c++', 'C++'),
		('python', 'Python'),
		('sql', 'SQL'),
		('web', 'HTML-CSS-Bootstrap'),
		('qt', 'Qt-PyQt5'),
		('git', 'GIT'),
		('linux', 'Linux'),
		('algorithms', 'Algorithms'),
		('network', 'Network'),
		('note', 'notes')
	)
	def category_default():
		return 'note'
	
	head = models.CharField(max_length = 30)
	description = models.CharField(max_length = 100)
	created_date = models.DateField(auto_now_add = True)
	author = models.CharField(max_length = 15, choices = author_choices)
	text = models.TextField()
	category = models.CharField(max_length = 15, choices = category_choices, default = category_default)
	
	@classmethod
	def month_sum(cls, year, month):
		return len(cls.objects.filter(created_date__year = year, created_date__month = month))
	
	@classmethod
	def year_sum(cls, year):
		return len(cls.objects.filter(created_date__year = year))
	
	def __str__(self):
		return self.head
