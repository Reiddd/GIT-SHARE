from django.http import HttpResponse, HttpResponseRedirect, Http404
from django.urls import reverse
from django.shortcuts import render, get_object_or_404, get_list_or_404
from datetime import date, timedelta
from .models import Blog

# Create your views here.

start_date = date(2018,2,16)
def sort_key(elem):
	return elem.created_date

#--------------

def index(request):
	context = {
		'current_year': date.today().year,
	}
	return render(request, 'blog/index.html', context)


def timeline(request, year):
	end_date = date.today()
	if year > end_date.year:
		return HttpResponseRedirect(reverse('timeline', args = (end_date.year,)))
	elif year < 2018:
		return HttpResponseRedirect(reverse('timeline', args = (2018,)))
		
	month_sum, year_sum, year_res = [], Blog.year_sum(year), year
	if year == end_date.year:
		month_list = sorted([x+1 for x in range(end_date.month)], reverse = True)
		month_sum = [{'name':'{}'.format(i), 'record':Blog.month_sum(end_date.year, i)} for i in month_list]
	else:
		month_list = sorted([1+_ for _ in range(12)], reverse = True)
		month_sum = [{'name':'{}'.format(x), 'record':Blog.month_sum(year, x)} for x in month_list]
	
	context = {
		'year': year_res,
		'month_list': month_list,
		'month_sum': month_sum,
		'year_sum': year_sum,
	}
	return render(request, 'blog/timeline.html', context)
	
	
def timeline_detail(request, year, month):
	if year == date.today().year:
		date_range = [i+1 for i in range(date.today().month)]
	else:
		date_range = list(range(1,13))
	blog_list = sorted(get_list_or_404(Blog, created_date__year = year, created_date__month = month), key = sort_key, reverse = True)
	context = {
		'current_year': year,
		'currnet_month': month,
		'total': len(blog_list),
		'blog_list': blog_list,
		'date_range': date_range,
	}
	return render(request, 'blog/timeline_detail.html', context)
	

def detail(request, Head):
	blog = get_object_or_404(Blog, head = Head)
	sidebar_links = [x[1] for x in Blog.category_choices]
	year = date.today().year
	context = {
		'blog': blog,
		'sidebar': sidebar_links,
		'year': year,
	}
	return render(request, 'blog/detail.html', context)


def category(request, target):
	match = tuple(filter(lambda x: x[1] == target, Blog.category_choices)) 
	
	try:
		blog_list = sorted(get_list_or_404(Blog, category = match[0][0]), key = sort_key, reverse = True)
	except IndexError:
		raise Http404('404 Not Found')
		
	section_list = [x[1] for x in Blog.category_choices]
	context = {
		'target': target,
		'current_year': date.today().year,
		'total': len(blog_list),
		'blog_list_front': dict(enumerate(blog_list[:6])),
		'section_list': section_list,
	}
	return render(request, 'blog/category.html', context)


def category_detail(request, target):
	match = tuple(filter(lambda x: x[1] == target, Blog.category_choices))
	
	try:
		blog_list = sorted(get_list_or_404(Blog, category = match[0][0]), key = sort_key, reverse = True)
	except IndexError:
		raise Http404('404 Not Found')
		
	section_list = [x[1] for x in Blog.category_choices]
	context = {
		'target': target,
		'current_year': date.today().year,
		'total': len(blog_list),
		'blog_list': blog_list,
		'section_list': section_list,
	}
	return render(request, 'blog/category_detail.html', context)
