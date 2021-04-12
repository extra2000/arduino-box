# -*- coding: utf-8 -*-
# vim: ft=sls

{%- set tplroot = tpldir.split('/')[0] %}
{%- from tplroot ~ "/map.jinja" import ARDUINOPROJECTS with context %}

{{ ARDUINOPROJECTS.rootdir }}:
  file.directory:
    - user: {{ ARDUINOPROJECTS.hostuser.name }}
    - group: {{ ARDUINOPROJECTS.hostuser.group }}

{{ ARDUINOPROJECTS.rootdir }}/files:
  file.recurse:
    - source: salt://arduinoprojects/files
    - user: {{ ARDUINOPROJECTS.hostuser.name }}
    - group: {{ ARDUINOPROJECTS.hostuser.group }}
    - show_changes: false
