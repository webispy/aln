Name:           aln
Version:        0.1.1
Release:        1%{?dist}
Summary:        Amazing Lucky Numbers - A library and tool for generating lucky numbers

License:        Apache-2.0
URL:            https://github.com/webispy/aln
Source0:        %{name}.tar.gz

BuildRequires:  cmake
BuildRequires:  gcc
BuildRequires:  gcc-c++
BuildRequires:  glib2-devel
BuildRequires:  doxygen

%description
Amazing Lucky Numbers (aln) is a library and tool for generating amazing lucky numbers.

%package libs
Summary:        Amazing Lucky Numbers Library
%description libs
A library for generating amazing lucky numbers.

%package devel
Summary:        Development files for the Amazing Lucky Numbers Library
Requires:       %{name}-libs = %{version}-%{release}
%description devel
Development files for the Amazing Lucky Numbers Library.

%prep
%setup -q -n %{name}

%build
%cmake
%cmake_build

# Generate man pages using Doxygen
doxygen
find doc/man/man3 -type f ! -name 'aln*' -exec rm -f {} \;

%install
%cmake_install

# Install man pages
mkdir -p %{buildroot}%{_mandir}/{man1,man3}
install -m 644 tool/aln.1 %{buildroot}%{_mandir}/man1/
install -m 644 doc/man/man3/* %{buildroot}%{_mandir}/man3/

%check
%ctest

%files
%license LICENSE
%{_bindir}/aln
%{_mandir}/man1/aln.1*

%files libs
%{_libdir}/libaln.so.*

%files devel
%{_includedir}/aln/
%{_libdir}/libaln.so
%{_libdir}/pkgconfig/aln.pc
%{_mandir}/man3/aln.h.3*
%{_mandir}/man3/aln_*.3*

%changelog
* Thu Jul 11 2024 Inho Oh <webispy@gmail.com> - 0.1.1
- fix aln.pc.in
- fix packaging
* Tue Jul 02 2024 Inho Oh <webispy@gmail.com> - 0.1.0-1
- Initial package
