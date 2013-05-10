Name:		ivykis
Summary:	event handling library
Group:		System Environment/Libraries
Version:	0.21
Release:	1
URL:		http://libivykis.sourceforge.net/
Source0:	ivykis-0.21.tar.gz
Packager:	Lennert Buytenhek <ivykis@wantstofly.org>
BuildRoot:	/tmp/%{name}-%{version}
License:	LGPLv2.1

%description
ivykis is an event handling library.

%prep
%setup -q -n %{name}-%{version}

%build
%configure
make

%install
rm -rf %{buildroot}
make DESTDIR=%{buildroot} install

%files
%defattr(-,root,root)
%{_includedir}/iv*
%{_libdir}/lib*
%{_libdir}/pkgconfig/*
%{_mandir}/man3/*

%clean
rm -rf %{buildroot}

%changelog
* Thu Apr 21 2011 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.21.

* Thu Mar 31 2011 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.20.

* Mon Nov 15 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.19.

* Sat Oct  9 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.18.

* Sat Sep 13 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.17.

* Sat Sep 10 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.16.

* Sat Sep  4 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.15.

* Mon Aug 16 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.14.

* Wed Aug 11 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Don't forget to install iv_avl.h as well.

* Wed Aug 11 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.13.

* Wed Jun  2 2010 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.12.

* Sun Feb  8 2009 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.11.

* Tue Jan  6 2009 Lennert Buytenhek <buytenh@wantstofly.org>
- Don't forget to install iv_fd_compat.h as well.

* Mon Jan  5 2009 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.10.

* Fri Jan  2 2009 Lennert Buytenhek <buytenh@wantstofly.org>
- Release ivykis 0.9.
