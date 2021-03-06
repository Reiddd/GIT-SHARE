# Generated by Django 2.0.2 on 2018-02-16 17:54

import blog.models
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('blog', '0005_auto_20180216_1735'),
    ]

    operations = [
        migrations.AlterField(
            model_name='blog',
            name='category',
            field=models.CharField(choices=[('c++', 'C++'), ('python', 'Python'), ('sql', 'SQL'), ('web', 'HTML/CSS/Bootstrap'), ('qt', 'Qt/PyQt5'), ('git', 'GIT'), ('linux', 'Linux'), ('algorithms', 'Algorithms'), ('network', 'Network'), ('note', 'notes')], default=blog.models.Blog.category_default, max_length=15),
        ),
    ]
