<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
    // -------------���X�Ҧ����ʩ��Ӹ��---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  purchase";
	$res = mysql_query($SQLStr);
    //--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<form name="form1" method="post" action="purchase/purchase_del2.php">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
    //--------------���ƿ�ܧe�{�γs��---------------
     echo "�R�����ʳ���&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=254&page=$i>$i</a>|";
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
             ���ʳ渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             ���~�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���ʼƶq
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���
            </td>             
          </tr>		  
	<?php
      //--------------��ܭ��Ʊ��ʩ��Ӹ�Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from purchase order by purchtranno limit $first , 10";
	  $res = mysql_query($SQLStr);	
       while (list($purchtranno, $purchprodno, $purchprodqty, $purchinqty, $purchpric)=mysql_fetch_row($res))
		{
       // ---------------������ʩ��Ӹ�ƪ���ƨçe�{------------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $purchtranno  . "</td>\n";
			echo "<td align='center'><a href='purchase/purchase_del2.php?purchprodno=" . $purchprodno . "&purchtranno=" .$purchtranno. "'>" . $purchprodno . "</a></td>\n";
			echo "<td align='center'>" . $purchprodqty . "</td>\n";	
			echo "<td align='center'>" . $purchpric . "</td>\n";			
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
	
