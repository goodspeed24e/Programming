<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
// -------------���X�Ҧ��i�f�檺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM transaction";
	$res = mysql_query($SQLStr);
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<form name="form1" method="post" action="ininv/ininvins_mod2.php">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�ק�i�f����&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=362&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?>   
	  
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             �i�f�渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             ���~�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���ʳ渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �i�f���
            </td>             
          </tr>		  
	<?php
//--------------��ܭ��ƶi�f���Ƨe�{�γs���קﭶ���\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from transaction order by tranpono limit $first , 10";
	  $res = mysql_query($SQLStr);	
       while (list($trancode, $trandate, $tranno, $tranpono, $tranremark, $tranvendno, $tranprodno, $tranprodname, $tranprodqty, $tranunit, $tranpric, $tranamt)=mysql_fetch_row($res))
		{
//---------------- ����i�f��ƪ���ƨçe�{--------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $tranno  . "</td>\n";
			echo "<td align='center'><a href='ininv/ininvins_mod2.php?tranprodno=" . $tranprodno . "&tranpono=" . $tranpono . "&tranno=" . $tranno . "'>" . $tranprodno . "</a></td>\n";
			echo "<td align='center'>";
			if ($tranpono == '') 
		         $tranpono="�L���~�s��";	        
			echo  $tranpono . "</td>\n";
			echo "<td align='center'>" . $trandate . "</td>\n";	
			echo "</tr>";		  	
		}	
?>
       </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
	
