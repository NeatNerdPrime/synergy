/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2012 - 2016 Symless Ltd.
 * SPDX-FileCopyrightText: (C) 2002 Chris Schoeneman
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "arch/Arch.h"

#if SYSAPI_WIN32
#include "arch/win32/ArchMiscWindows.h"
#endif

//
// Arch
//

Arch *Arch::s_instance = nullptr;

Arch::Arch()
{
  assert(s_instance == nullptr);
  s_instance = this;
}

Arch::Arch(Arch *arch)
{
  s_instance = arch;
}

void Arch::init()
{
  ARCH_NETWORK::init();
#if SYSAPI_WIN32
  ArchMiscWindows::init();
#endif
}

Arch *Arch::getInstance()
{
  assert(s_instance != nullptr);
  return s_instance;
}
