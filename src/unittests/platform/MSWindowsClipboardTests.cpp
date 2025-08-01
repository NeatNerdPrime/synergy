/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 Chris Rizzitello <sithlord48@gmail.com>
 * SPDX-FileCopyrightText: (C) 2012 - 2016 Symless Ltd.
 * SPDX-FileCopyrightText: (C) 2002 Chris Schoeneman
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "MSWindowsClipboardTests.h"

#include "platform/MSWindowsClipboard.h"

void MSWindowsClipboardTests::initTestCase()
{
  m_arch.init();
  m_log.setFilter(LogLevel::Debug2);

  MSWindowsClipboard clipboard(NULL);

  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.empty());
}

void MSWindowsClipboardTests::cleanupTestCase()
{
  initTestCase();
}

void MSWindowsClipboardTests::emptyUnusedClipboard()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.emptyUnowned());
}

void MSWindowsClipboardTests::emptyOpenCalled()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.empty());
}

void MSWindowsClipboardTests::emptySingleFormat()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));

  clipboard.add(IClipboard::Format::Text, m_testString);
  QVERIFY(clipboard.empty());
  QVERIFY(!clipboard.has(IClipboard::Format::Text));
}

void MSWindowsClipboardTests::addValue()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));

  clipboard.add(IClipboard::Format::Text, m_testString);
  QCOMPARE(clipboard.get(IClipboard::Format::Text), m_testString);
}

void MSWindowsClipboardTests::replaceValue()
{
  using enum IClipboard::Format;

  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));

  clipboard.add(Text, m_testString);
  clipboard.add(Text, m_testString2);

  QCOMPARE(clipboard.get(Text), m_testString2);
}

void MSWindowsClipboardTests::openTimeIsOne()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(1));
}

void MSWindowsClipboardTests::closeIsOpen()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(1));
  clipboard.close();
}

void MSWindowsClipboardTests::getTimeOpenWithNoEmpty()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(1));
  // this behavior is different to that of Clipboard which only
  // returns the value passed into open(t) after empty() is called.
  QCOMPARE(clipboard.getTime(), 1);
}

void MSWindowsClipboardTests::getTimeOpenAndEmpty()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(1));
  QVERIFY(clipboard.empty());
  QCOMPARE(clipboard.getTime(), 1);
}

void MSWindowsClipboardTests::has_withFormatAdded()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.empty());

  clipboard.add(IClipboard::Format::Text, m_testString);
  QVERIFY(clipboard.has(IClipboard::Format::Text));
}

void MSWindowsClipboardTests::has_withNoFormatAdded()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.empty());
  QCOMPARE(clipboard.get(IClipboard::Format::Text), "");
}

void MSWindowsClipboardTests::getNonEmptyText()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.empty());

  clipboard.add(IClipboard::Format::Text, m_testString);
  QCOMPARE(clipboard.get(IClipboard::Format::Text), m_testString);
}

void MSWindowsClipboardTests::isOwnedByDeskflow()
{
  MSWindowsClipboard clipboard(NULL);
  QVERIFY(clipboard.open(0));
  QVERIFY(clipboard.isOwnedByDeskflow());
}

QTEST_MAIN(MSWindowsClipboardTests)
