<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�t�����I�b�ڪ�vendaprec</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>
<?php
$dt1=date("Y-m-d");
$dt2=date("Y-m-d");
?>
<body >
<form name='form1' method='post' action='vend/vendaprec_prt2.php?trandate1=" . $row[trandate1] . "&trandate2=" . $row[trandate2] . "&tranvendno1" . $row[tranvendno] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		�t�����I�b�ڪ�
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133"  >
		<br>		<br>		<p>�i�f���
            </p>
		<p>
<!--��J���I�b�ڦC�L����----------------->		
		  <input type="text" name="trandate1" size="10" value="<?=$dt1;?>">
		  ��
		  <input type="text" name="trandate12" size="10" value="<?=$dt2;?>">
		</p>
		<p>�t�ӽs��		</p>
		<p>
		  <input type="text" name="tranvendno" size="10" value="<?='0000000000'?>">

</p>
		<p>
            <input type="submit" name="Submit" value="�C�L" >
          </p>
          <p >&nbsp;          </p></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
</body>
</html>
