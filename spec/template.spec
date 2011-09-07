Name: name
Version: 1.0
Release: 1
Summary: summary
Summary(ja_JP.utf8): サマリー
URL: http://www.example.com/
License: license
Group: System/Libraries
Source: %{name}-%{version}.tar.gz
#NoSource: 0

BuildRoot: %{_tmppath}/%{name}-%{version}-build

%description
description.

%description -l ja_JP.utf8
記述。

%package devel
Summary: %{name} Development
Group: Development/Libraries/C and C++

%description devel
%{name}-devel contains the files necessary to compile %{name} applications and utilities.

%prep
%setup

%build
%configure
%__make

%install
%__rm -rf $RPM_BUILD_ROOT
%makeinstall

%post
ldconfig -n %{_libdir}

%postun
ldconfig -n %{_libdir}

%files
%defattr(-, root, root)
%doc CHANGELOG COPYING CREDITS README TODO
%{_bindir}/*
%{_libdir}/*.so.*

%files devel
%defattr(-, root, root)
%{_libdir}/*.so
%{_libdir}/*.a
%{_includedir}/SDL/*

%changelog

* Tue Jan 25 2005 Kiichiro NAKA <knaka@turbolinux.co.jp> 1.0.1-1
- new version
