// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2009-2010 Dreamhost
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software
 * Foundation.  See file COPYING.
 *
 */

#include <iostream>
#include <list>
#include <set>

using std::string;

static bool get_next_token(const std::string &s, size_t& pos, string ignore, string& token)
{
  string delims = ";,= \t";
  const char *pos_delims[] = {";", ",", "=", " ", "\t", NULL};

  if (!ignore.empty()) {
    delims.clear();

    for (const char **d = pos_delims; *d; ++d) {
      size_t pos = ignore.find(*d);
      if (pos == string::npos)
         delims.append(*d);
    }
  }

  int start = s.find_first_not_of(" \t", pos);
  int end;

  if (start < 0)
    return false;

  if (s[start] == ',') {
    end = start + 1;
    pos = end;
  } else {
    end = s.find_first_of(delims.c_str(), start+1);
    if (end >= 0)
      pos = end + 1;
  }

  if (end < 0) {
    end = s.size();
    pos = end;
  }

  token = s.substr(start, end - start);
  return true;

}

void get_str_list(const std::string& str, const char *ignore_,
        std::list<std::string>& str_list)
{
  size_t pos = 0;
  string token;
  string ignore = ignore_;

  str_list.clear();

  while (pos < str.size()) {
    if (get_next_token(str, pos, ignore, token)) {
      if (token.size() > 0) {
        str_list.push_back(token);
      }
    }
  }
}

void get_str_list(const std::string& str, std::list<string>& str_list)
{
  size_t pos = 0;
  string token;

  str_list.clear();

  while (pos < str.size()) {
    if (get_next_token(str, pos, "", token)) {
      if (token.size() > 0) {
        str_list.push_back(token);
      }
    }
  }
}

void get_str_set(const std::string& str, std::set<std::string>& str_set)
{
  size_t pos = 0;
  string token;

  str_set.clear();

  while (pos < str.size()) {
    if (get_next_token(str, pos, "", token)) {
      if (token.size() > 0) {
        str_set.insert(token);
      }
    }
  }
}
