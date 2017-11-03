/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CHARTTIP_H
#define CHARTTIP_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>

class ChartTip : public QGraphicsItem
{
public:
	ChartTip( QtCharts::QChart* a_pParent );

	void SetText( const QString& a_rText );
	void SetAnchor( QPointF a_point );
	void UpdateGeometry();

protected:
	void paint( QPainter* a_pPainter, const QStyleOptionGraphicsItem* a_pOption, QWidget* a_pWidget );
	void mousePressEvent( QGraphicsSceneMouseEvent* a_pEvent );
	void mouseMoveEvent( QGraphicsSceneMouseEvent* a_pEvent );

	QRectF boundingRect() const;

private:
	QString m_strText;
	QRectF m_textRect;
	QRectF m_rect;
	QPointF m_anchor;
	QFont m_font;
	QtCharts::QChart* m_pChart;
};

#endif // CHARTTIP_H
