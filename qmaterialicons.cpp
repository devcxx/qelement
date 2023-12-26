/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 David Krepsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file qmaterialicons.cpp
 *
 * \brief QMaterialIcons library code.
 *
 * This file contains the implementation of the QMaterialIcons class.
 *
 * \author David Krepsky
 * \version 0.1.0
 * \date 05/2016
 * \copyright David Krepsky
 *
 * \bug None known.
 */

#include "qmaterialicons.h++"
#include <QDebug>
#include <QFontDatabase>
#include <QPainter>

// Initialize the instance handler.
QMaterialIcons *QMaterialIcons::m_instance = NULL;

// Create the singleton instance.
void QMaterialIcons::load() {
  Q_ASSERT_X(NULL == m_instance, "QMaterialIcons library",
             "Library loaded twice.");

  if (NULL == m_instance) {
    m_instance = new QMaterialIcons();
    if (NULL == m_instance) {
      qDebug() << "Failed to alloc QMaterialIcons instance.";
    }
  }
}

// Destroy the singleton instance.
void QMaterialIcons::unload() {
  Q_ASSERT_X(NULL == m_instance, "QMaterialIcons library",
             "Library is already unloaded.");

  if (NULL != m_instance) {
    delete m_instance;
    m_instance = NULL;
  }
}

// Returns the QMaterialIcons font.
QFont QMaterialIcons::getFont() {
  Q_ASSERT_X(NULL != m_instance, "QMaterialIcons library",
             "Library not loaded.");

  // Check if resources are loaded.
  if (NULL == m_instance) {
    return QFont();
  }

  // Returns the font.
  return m_instance->m_font;
}

// Returns an icon pixmap.
QPixmap QMaterialIcons::getPixmap(mi::icon icon, QColor color, int size) {
  Q_ASSERT_X(NULL != m_instance, "QMaterialIcons library",
             "Library not loaded.");

  // Check if resources are loaded.
  if (NULL == m_instance) {
    return QPixmap();
  }

  // Create a new pixmap with size x size pixels and transparent background.
  QPixmap pix(size, size);
  pix.fill(Qt::transparent);

  // Set painting options.
  QPainter painter(&pix);
  QFont painterFont = m_instance->getFont();
  painterFont.setPixelSize(size);
  painter.setFont(painterFont);
  painter.setPen(color);

  // Draw icon.
  painter.drawText(0, size, QChar(icon));
  return pix;
}

// Returns a QIcon icon.
QIcon QMaterialIcons::getIcon(mi::icon icon, QColor color, int size) {

  // Sanity check is skipped because getPixmap will return an empty pixmap if
  // something is wrong.
  return QIcon(getPixmap(icon, color, size));
}

// Class constructor.
QMaterialIcons::QMaterialIcons() {
  // Load font resource. This is necessary in libraries.
  Q_INIT_RESOURCE(font);

  // Load font into Qt.
  int id = QFontDatabase::addApplicationFont(":/font/materialicons.ttf");

  // Load successful?
  if (id != -1) {
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    m_font = QFont(family);
  } else {
    qDebug() << "Error loading QMaterialIcons font.";
  }
}

// Class destructor.
QMaterialIcons::~QMaterialIcons() {
  // Free font resource.
  Q_CLEANUP_RESOURCE(font);
}
