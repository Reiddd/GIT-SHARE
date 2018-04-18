from django.urls import path, re_path
from . import views

urlpatterns = [
	path('', views.index, name = 'index'),
	path('timeline-<int:year>/', views.timeline, name = 'timeline'),
	path('month-detail-<int:year>-<int:month>', views.timeline_detail, name = 'timeline_detail'),
	path('category-detail-<str:target>/', views.category_detail, name = 'category_detail'),
	path('category-<str:target>/', views.category, name = 'category'),
	re_path(r'(?P<Head>.+)/', views.detail, name = 'detail'),
]
